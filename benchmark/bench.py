import subprocess
import time
import math
import pandas

plc_address = "192.168.0.150"
plc_port = "2000"

benchmark_path_list = [
    "empty/empty.st",
    "delay/delay.st",
    "optimize_real/optimize.st",
    "optimize_lreal/optimize.st"
]


optimization_flag_list = [
    "-O0",
    "-O1",
    "-O2",
    "-O3",
    "-Ofast",
    "-Os",
    "-Oz"
]


benchmark_path = benchmark_path_list[0]
optimization_flag = optimization_flag_list[0]

output_path = "build/output.package"

st_lang = ".\\..\\build\\build\\bin\\stlang.exe"
plc_conn = ".\\..\\build\\build\\bin\\plc_conn.exe"


def Execute(args):
    # print(" ".join(args))
    result = subprocess.run(args, capture_output=True, text=True)
    # print(result.stdout)
    if result.returncode != 0:
        print(result.stdout)
        exit(-1)
    return result


result = Execute([plc_conn, "--address", plc_address,
                  "--port", plc_port, "--performance"])


print(result.stdout)

# def MeasurementsToDictionary(raw):
#     measurements = {}

#     lines = raw.split("\n")
#     for line in lines:
#         if line == "":
#             continue

#         line_splited = line.split(" ")

#         measurement_name = line_splited[1]

#         count = int(line_splited[2][2:])
#         elapsed_time = float(line_splited[3][2:])
#         variance = float(line_splited[4][2:])
#         std_deviation = math.sqrt(variance)

#         measurements[measurement_name] = {
#             "count": count,
#             "elapsed_time": elapsed_time,
#             "std_deviation": std_deviation,
#             "variance": variance
#         }

#     return measurements

def MeasurementsToDictionary(raw):
    measurements = {}

    lines = raw.split("\n")
    for line in lines:
        if line == "":
            continue

        line_splited = line.split(" ")

        measurement_name = line_splited[1]

        count = int(line_splited[2][2:])
        elapsed_time = float(line_splited[3][2:])
        variance = float(line_splited[4][2:])
        std_deviation = math.sqrt(variance)

        measurements[measurement_name] = {
            "count": count,
            "elapsed_time": elapsed_time,
            "std_deviation": std_deviation,
            "variance": variance
        }

    return measurements

measurements = MeasurementsToDictionary(result.stdout)



print(measurements)

collected_data = pandas.DataFrame(measurements).transpose()
collected_data["count"] = collected_data["count"].astype('Int64')

print(collected_data)

with pandas.ExcelWriter('test.xlsx', engine='xlsxwriter') as writer:
    # write label
    label = pandas.DataFrame(["XD"])
    label.to_excel(writer, startrow=0 , startcol=0, index=False, header=False, sheet_name="Sheet1")  

    # write data
    collected_data.to_excel(writer, startrow=2 , startcol=0, sheet_name="Sheet1")   

    workbook = writer.book
    worksheet = writer.sheets['Sheet1']

    