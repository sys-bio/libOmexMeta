import os, sys, subprocess, glob
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--build-root", help="absolute path to where you are building libomexmeta",  type=str)
parser.add_argument("--pyomexmeta-site-package-dir", help="absolute path to where the pyomexmeta site package dir", type=str)
parser.add_argument("--output-location", help="where to save the output from examples", type=str)
args = parser.parse_args()

print("\n\n================================================")
print("Generating libOmexMeta documentation examples ")
print("====================================================")
print("Documentation examples are run every time the docs are built. ")
print("The doc examples are run from the install folder so you must ")
print("ensure you have just build the install cmake target before ")
print("building the documentation. ")
print("Arguments used are: ")
print("\tbuild_root:", args.build_root)
print("\toutput_location", args.output_location)
print("\tpyomexmeta_site_package_dir", args.pyomexmeta_site_package_dir)
print("\t", args)

# Examples are excuted from the install folder, not the build folder.
# Therefore we must ensure the install folder exists and is updated
print("")

# Advance warning for when pyomexmeta is installed in site-packages
# since this will be used for generating examples and docs
# rather than the new version in source
if "pyomexmeta" in sys.modules:
    raise ValueError("pyomexmeta is a package in in your python installation "
                     "which probably means that you have a local copy "
                     "of pyomexmeta installed. In this is the case, then "
                     "the installed copy will be used for running examples "
                     "and generating documentation, which is *not* what you want. "
                     "Please run `pip uninstall pyomexmeta` and/or check "
                     "your are using the correct Python environment.")

CURRENT_DIRECTORY = DOCS_DIRECTORY = os.path.join(os.path.dirname(__file__))
PYTHON_FILES = glob.glob(os.path.join(DOCS_DIRECTORY, "*/*/*.py"))

# We do not want to include test binaries when we search for example binaries to run
EXCLUSION_LIST = [

]

if sys.platform == "win32":
    ext = ".exe"
elif sys.platform == "unix" :
    ext = ".a"
elif sys.platform == "darwin":
    ext = ''
else:
    raise ValueError("No platform")

EXCLUSION_LIST = [i + ext for i in EXCLUSION_LIST]

# USER SUPPLIED
BUILD_ROOT_DIR = os.path.join(args.build_root, "bin")
print("BUILD_ROOT_DIR:\n\t", BUILD_ROOT_DIR)

print("================================================")
BINARY_FILES = glob.glob(os.path.join(BUILD_ROOT_DIR, "*"+ext))

for exclusion in EXCLUSION_LIST:
    BINARY_FILES = [i for i in BINARY_FILES if exclusion not in i]

print("Example binary files for execution: ")
for i in BINARY_FILES:
    print("\t", i)
print("Example python files for execution: ")
for i in PYTHON_FILES:
    print("\t", i)

# we must prepend this to any python file that gets executed.
path_code = f"""
import sys
import os
sys.path.append('{args.pyomexmeta_site_package_dir}')
"""


def run_python_files():
    for python_file in PYTHON_FILES:
        print(f"running \"{python_file}\"")
        with open(python_file, "r") as f:
            python_code = f.read()
        python_code = path_code + python_code

        tmp = os.path.join(os.path.dirname(__file__), f"tmp_{os.path.split(python_file)[1]}")
        with open(tmp, "w") as f:
            f.write(python_code)

        output = subprocess.check_output([sys.executable, tmp])

        os.remove(tmp)

        output_filename = os.path.split(os.path.splitext(python_file)[0])[1]

        output_filename = os.path.join(args.output_location, output_filename +".txt")
        with open(output_filename, "wb") as f:
            f.write(output)
        print(f"output written to \"{output_filename}\"")


def run_binary_files():
    for binary in BINARY_FILES:
        print(f"running binary file \"{binary}\"")
        print("Exists: " , os.path.isfile(binary))
        try:
            output = subprocess.check_output([binary])
        except subprocess.CalledProcessError as e:
            print(e)
            # exit(1)
        # print(output.decode())

        output_filename = os.path.split(os.path.splitext(binary)[0])[1]

        output_filename = os.path.join(args.output_location, output_filename + ".txt")
        with open(output_filename, "w") as f:
            try:
                f.write(output.decode())
            except UnicodeDecodeError: # for python programs that produce diagrams
                continue

        print(f"output written to \"{output_filename}\"")



if __name__ == "__main__":
    run_python_files()
    run_binary_files()


















