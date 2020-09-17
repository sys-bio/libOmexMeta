import os, sys, subprocess, glob
import tempfile

CURRENT_DIRECTORY = DOCS_DIRECTORY = os.path.join(os.path.dirname(__file__))
PYTHON_FILES = glob.glob(os.path.join(DOCS_DIRECTORY, "*/*/*.py"))

EXCLUSION_LIST = [
    "OmexMetaCAPITests",
    "OmexMetaTests",
    "redland-wrapper-tests",
]

if sys.platform == "win32":
    ext = ".exe"
elif sys.platform == "unix":
    ext = ".a"
else:
    raise ValueError("No platform")

EXCLUSION_LIST = [i + ext for i in EXCLUSION_LIST]

# USER SUPPLIED
INSTALL_FOLDER = r"D:\libOmexMeta\install-msvc"

OUTPUT_LOCATION = r"D:\libOmexMeta\docs\ExampleOutputFiles"
INSTALL_BIN_FOLDER = os.path.join(INSTALL_FOLDER, "bin")
PYOMEXMETA_SOURCE_DIR = r"D:\libOmexMeta\src"

sys.path.append(PYOMEXMETA_SOURCE_DIR)

BINARY_FILES = glob.glob(os.path.join(INSTALL_BIN_FOLDER, "*"+ext))

for exclusion in EXCLUSION_LIST:
    BINARY_FILES = [i for i in BINARY_FILES if exclusion not in i]

if "CreatePhysicalEntityCpp" not in [os.path.splitext(os.path.split(i)[1])[0] for i in BINARY_FILES]:
    raise ValueError("Program CreatePhysicalEntityCpp not listed in your binary files. There is probably a problem.")

# we must prepend this to any python file that gets executed.
path_code = f"""
import sys
sys.path.append('{PYOMEXMETA_SOURCE_DIR}')
"""


def run_python_files():
    for python_file in PYTHON_FILES:
        print(f"running \"{python_file}\"")
        with open(python_file, "r") as f:
            python_code = f.read()
        python_code = path_code + python_code

        tmp = os.path.join(os.path.dirname(__file__), "tmp.py")
        with open(tmp, "w") as f:
            f.write(python_code)

        output = subprocess.check_output([sys.executable, tmp])

        os.remove(tmp)

        output_filename = os.path.split(os.path.splitext(python_file)[0])[1]

        output_filename = os.path.join(OUTPUT_LOCATION, output_filename +".txt")
        with open(output_filename, "w") as f:
            f.write(output.decode())
        print(f"output written to \"{output_filename}\"")


def run_binary_files():
    for binary in BINARY_FILES:
        print(f"running binary file \"{binary}\"")
        try:
            output = subprocess.check_output([binary])
        except subprocess.CalledProcessError as e:
            print(e)
            exit(1)

        output_filename = os.path.split(os.path.splitext(binary)[0])[1]

        output_filename = os.path.join(OUTPUT_LOCATION, output_filename + ".txt")
        with open(output_filename, "w") as f:
            f.write(output.decode())

        print(f"output written to \"{output_filename}\"")


if __name__ == "__main__":
    run_binary_files()
    run_python_files()


















