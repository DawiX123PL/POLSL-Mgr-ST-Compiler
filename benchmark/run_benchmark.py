import subprocess
import time
import pandas
import math
import os
import os.path
import json
from pathlib import Path
from termcolor import colored, cprint

# benchmark_type = "FAST"
# benchmark_type = "ACCURATE"
benchmark_type = "BUILD_ONLY"

plc_address = "192.168.0.150"
plc_port = "2000"

st_lang =  ".\\build\\build\\bin\\stlang.exe"
plc_conn = ".\\build\\build\\bin\\plc_conn.exe"

relative_path = "" if os.path.isfile(st_lang) else ".\\..\\" 

st_lang =  relative_path + st_lang
plc_conn = relative_path + plc_conn

benchmark_path_list = [
    relative_path + "benchmark/empty/empty.st",
    relative_path + "benchmark/delay/delay.st",
    relative_path + "benchmark/optimize_real/optimize.st",
    relative_path + "benchmark/optimize_lreal/optimize.st"
]

optimization_flag_list = [
    "-O0",
    "-O1",
    "-O2",
    "-O3",
    ["-O3", "-ffast-math"],
    "-Os",
    "-Oz"
]

output_name = "output.package"
output_elf_name = "output.elf"

build_path = relative_path + "benchmark/build/"
# output_file = output_path + output_name
# output_elf_file = output_path + output_elf_name

# def FlagToStr(flag_list):
def FlatList(l):
    l1 = []
    for e in l:
        if type(e) is list:
            l1 += FlatList(e)
        else:
            l1.append(e)
    return l1

def Execute(args, show_output=False):
    # print(" ".join(args))
    # check if file exists
    args = FlatList(args)
    result = subprocess.run(args, capture_output=True, text=True)
    # print(result.stdout)
    if result.returncode != 0:
        cprint(result.stdout, "red")
        # exit(-1)

    if show_output :
        print(result.stdout)
    return result

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

def RunBenchmark(benchmark_path, optimization_flag, *, output_file, output_elf_file):
    # step 1 compile
    print("Compiling code")
    try:
        Execute([st_lang,
                benchmark_path, optimization_flag, "-o", output_file])
        
        # run optimization as separate pass
        # opt output.ll -Os -S -o output_opt.ll
        output_opt_file =  Path(output_file).parent / "output_opt.ll"
        output_ll_file =  Path(output_file).parent / "output.ll"
        # Execute(["opt", str(output_ll_file), optimization_flag, "-S", "-o", str(output_opt_file)])
        Execute(["clang",optimization_flag, "-emit-llvm", "-S", str(output_ll_file), "-o", str(output_opt_file), "--target=thumbv7em-none-unknown-eabi"])
        
        #  llvm-size build/output.elf 
        Execute(["llvm-size", "--radix=10", output_elf_file], show_output=True)
    except:
        pass

    time.sleep(1)

    # step 2 upload code
    print("Stop PLC")
    Execute([plc_conn, "--address", plc_address,
            "--port", plc_port, "--stop",  "--verbose"])
    time.sleep(1)

    print("Uploading")
    Execute([plc_conn, output_file, "--address", plc_address,
            "--port", plc_port, "--upload", "--performance", "--verbose"])
    time.sleep(1)

    # step 3 repeatedly shutdown and start up PLC

    print("Repeatedly starting and stopping plc")
    for i in range(16):
        print(f"i = {i}")
        Execute([plc_conn, "--address", plc_address,
                "--port", plc_port, "--start",  "--verbose"])
        time.sleep(2)

        Execute([plc_conn, "--address", plc_address,
                "--port", plc_port, "--stop",  "--verbose"])
        time.sleep(2)

    # step 4 - run code for one minute
    print("Running code")
    Execute([plc_conn, "--address", plc_address,
            "--port", plc_port, "--start",  "--verbose"])
    time.sleep(60)

    # step 5 - read performance
    result = Execute([plc_conn, "--address", plc_address,
                    "--port", plc_port, "--performance"])

    print("Benchmark finished")

    return result



def RunBenchmarkFast(benchmark_path, optimization_flag, *, output_file, output_elf_file):
    # step 1 compile
    print("Compiling code")
    
    try:
        Execute([st_lang,
                benchmark_path, optimization_flag, "-o", output_file])
        
        # run optimization as separate pass
        # opt output.ll -Os -S -o output_opt.ll
        output_opt_file =  Path(output_file).parent / "output_opt.ll"
        output_ll_file =  Path(output_file).parent / "output.ll"
        # Execute(["opt", str(output_ll_file), optimization_flag, "-S", "-o", str(output_opt_file)])

        Execute(["clang",optimization_flag, "-emit-llvm", "-S", str(output_ll_file), "-o", str(output_opt_file), "--target=thumbv7em-none-unknown-eabi"])

        #  llvm-size build/output.elf 
        Execute(["llvm-size", "--radix=10", output_elf_file], show_output=True)

    except:
        pass

    time.sleep(1)

    # step 2 upload code
    print("Stop PLC")
    Execute([plc_conn, "--address", plc_address,
            "--port", plc_port, "--stop",  "--verbose"])
    time.sleep(1)

    print("Uploading")
    Execute([plc_conn, output_file, "--address", plc_address,
            "--port", plc_port, "--upload", "--performance", "--verbose"])
    time.sleep(1)

    # step 3 repeatedly shutdown and start up PLC
    # SKIP

    # step 4 - run code for one minute
    print("Running code")
    Execute([plc_conn, "--address", plc_address,
            "--port", plc_port, "--start",  "--verbose"])
    time.sleep(2)

    # step 5 - read performance
    result = Execute([plc_conn, "--address", plc_address,
                    "--port", plc_port, "--performance"])

    print("Benchmark finished")
    return result


def BuildOnly(benchmark_path, optimization_flag, *, output_file, output_elf_file):
    print("Compiling code")
    
    try:
        Execute([st_lang,
                benchmark_path, optimization_flag, "-o", output_file])
        
        # run optimization as separate pass
        # opt output.ll -Os -S -o output_opt.ll
        output_opt_file =  Path(output_file).parent / "output_opt.ll"
        output_ll_file =  Path(output_file).parent / "output.ll"
        # Execute(["opt", str(output_ll_file), optimization_flag, "-S", "-o", str(output_opt_file)])

        Execute(["clang",optimization_flag, "-emit-llvm", "-S", str(output_ll_file), "-o", str(output_opt_file), "--target=thumbv7em-none-unknown-eabi"])

        #  llvm-size build/output.elf 
        Execute(["llvm-size", "--radix=10", output_elf_file], show_output=True)

    except:
        pass

def WriteResultToFile(name, collected_data):
    Path(name).parent.mkdir(parents=True,exist_ok=True)
    with pandas.ExcelWriter(name, engine='xlsxwriter') as writer:

        for key, table in collected_data.items():
            table.to_excel(writer, index=True, header=True, sheet_name=key)


for benchmark_path in benchmark_path_list:
    # start_col_nr = 0
    collected_measurements = {}

    for optimization_flag in optimization_flag_list:
        cprint(benchmark_path + " " + str(optimization_flag), color="cyan")

        output_path = Path(build_path) / (Path(benchmark_path).parent.name + "".join(optimization_flag))
        output_file = output_path / output_name
        output_elf_file = output_path / output_elf_name

        Path(output_path).mkdir(parents=True,exist_ok=True)
        if benchmark_type == "FAST":
            result = RunBenchmarkFast(
                benchmark_path, 
                optimization_flag,
                output_elf_file=str(output_elf_file),
                output_file=str(output_file))
            
        if benchmark_type == "ACCURATE":
            result = RunBenchmark(
                benchmark_path, 
                optimization_flag,
                output_elf_file=str(output_elf_file),
                output_file=str(output_file))
            
        if benchmark_type == "BUILD_ONLY":
            BuildOnly(
                benchmark_path, 
                optimization_flag,
                output_elf_file=str(output_elf_file),
                output_file=str(output_file))
            
        if benchmark_type != "BUILD_ONLY":
            measurements = MeasurementsToDictionary(result.stdout)

            table = pandas.DataFrame(measurements).transpose()
            table["count"] = table["count"].astype('Int64')

            collected_measurements["".join(optimization_flag)] = table

    if benchmark_type != "BUILD_ONLY":
        result_file_name = "./result/" + Path(benchmark_path).parent.name + "_benchmark.xlsx"
        WriteResultToFile(result_file_name, collected_measurements)


cprint("All benchmarks finished", color="light_green")


