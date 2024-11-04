import pandas as pd
from pathlib import Path
import uncertainties
from uncertainties_pandas import UncertaintyArray, UncertaintyDtype
from uncertainties import ufloat, umath, unumpy


source_table = "result/tmp_empty_benchmark.xlsx"
result_folder = "./latex_table"
result_name = "empty"


def SaveResult(*, name, data):
    Path(name).parent.mkdir(parents=True, exist_ok=True)
    with open(str(name), "w") as file:
        file.write(data)


def UfloatToLatex(uf):
    if abs(uf.std_dev) < 0.0001:
        return "${:L}$".format(uf)
    else:
        return "${0:.2uL}$".format(uf)


def TableToUncertainVector(data, column):
    pairs = zip(data["elapsed_time"], data["std_deviation"])
    vector = [ufloat(p[0], p[1]) for p in pairs]
    udata = pd.DataFrame(vector, data.index, [column])
    return udata


def MergeUncertainTables(table_dictionary):
    return pd.concat([TableToUncertainVector(table, flag) for flag, table in table_dictionary.items()], axis=1)

    # for flag, table in table_dictionary.items():
    #     udata = TableToUncertainVector(data, flag)


def ToLatex(table, unit=None, label_to_latex=True):

    if unit == "s":
        multiplier = 1
        latex_unit = "s"

    if unit == "ms":
        multiplier = 1000
        latex_unit = "ms"

    if unit == "us":
        multiplier = 1000 * 1000
        latex_unit = "$\mu$s"

    if unit == None:
        multiplier = 1
        latex_unit = ""

    if label_to_latex:
        def label_to_latex(s): return "$T_{{{}}}$, {}".format(
            s.replace("_", "\\_"), latex_unit)
        table = table.rename(label_to_latex, axis=1)

    table = table * multiplier

    formatter_list = [UfloatToLatex for _ in table.columns]
    return table.to_latex(formatters=formatter_list)


def ProcessTable(*, source_table, result_name):

    raw_tables = pd.read_excel(source_table, sheet_name=None, index_col=0)

    table = MergeUncertainTables(raw_tables)
    table = table.transpose()

    scan_time = table[["MOD_UPDATE", "EXEC", "REQ"]].sum(axis=1)
    first_scan_time = table[["MOD_UPDATE",
                             "START_SEQ", "EXEC_FS", "REQ"]].sum(axis=1)

    scan_table = pd.DataFrame(
        {"SCAN": scan_time, "FIRST_SCAN": first_scan_time})

    print(ToLatex(table.iloc[:, 0:3], "us"))
    print(ToLatex(table.iloc[:, 3:], "us"))
    print(ToLatex(scan_table, "us"))

    Path(result_folder) / result_name

    SaveResult(name=Path(result_folder) / result_name /
               "table1.tex", data=ToLatex(table.iloc[:, 0:3], "us"))
    SaveResult(name=Path(result_folder) / result_name /
               "table2.tex", data=ToLatex(table.iloc[:, 3:], "us"))
    SaveResult(name=Path(result_folder) / result_name /
               "scan_table.tex", data=ToLatex(scan_table, "ms"))


ProcessTable(source_table="result/empty_benchmark.xlsx",
             result_name="empty")

ProcessTable(source_table="result/delay_benchmark.xlsx",
             result_name="delay")

ProcessTable(source_table="result/optimize_real_benchmark.xlsx",
             result_name="optimize_real")

ProcessTable(source_table="result/optimize_lreal_benchmark.xlsx",
             result_name="optimize_lreal")


raw_tables = pd.read_excel(
    "result/optimize_real_benchmark.xlsx", sheet_name=None, index_col=0)
table_real = MergeUncertainTables(raw_tables).transpose()

raw_tables = pd.read_excel(
    "result/optimize_lreal_benchmark.xlsx", sheet_name=None, index_col=0)
table_lreal = MergeUncertainTables(raw_tables).transpose()

vec_real = table_real["EXEC"]
vec_lreal = table_lreal["EXEC"]


comparison = pd.DataFrame({
    "optimize\\_real.st ($T_{EXEC1}$, ms)": vec_real * 1000, 
    "optimize\\_lreal.st ($T_{EXEC2}$, ms)": vec_lreal * 1000,
    "$\\frac{T_{EXEC2}}{T_{EXEC1}}$" : vec_lreal / vec_real
    })

result_file = Path(result_folder) / "real_lreal_comp.tex"

SaveResult(name=result_file, data=ToLatex(comparison, None, False))

print(comparison)


