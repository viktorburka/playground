import ComponentsLoaderXml as Loader
import subprocess
import os
import sys


def tfs_path_to_local_path(tfs_path, tprefix, lprefix):
    if not tfs_path.startswith(tprefix):
        return ""
    local_path = tfs_path.replace(tprefix, lprefix, 1).replace("/", "\\")
    return local_path


def build(path, command):
    print("Navigate to: ", path)
    print("And call: ", command)
    try:
        os.chdir(path)
    except:
        print("Error: ", sys.exc_info()[0])
    subprocess.call([command])

components_list     = []
changed_files_list  = []
components_to_build = []
prefix              = ""

loader = Loader.ComponentsLoaderXml('components.xml')

if loader.load():
    components_list = loader.components()
    prefix = loader.prefix
    print('prefix: ', prefix)

tf_cmd  = "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\TF.exe"
arg1 = "status"
arg2 = "/shelveset:"
arg3 = "/format:detailed"

out = subprocess.check_output([tf_cmd, arg1, arg2, arg3], universal_newlines=True)
print("type: ", type(out))
print(out)

str_list = out.splitlines()

for line in str_list:
    if line.startswith("$"):
        changed_file_tpath = line.split(";")[0]
        changed_files_list.append(changed_file_tpath)

for f in changed_files_list:
    print(f)

for changed_file_tpath in changed_files_list:
    for component in components_list:
        if changed_file_tpath.startswith(component.tfsPath) or changed_file_tpath.startswith(component.testTfsPath):
            components_to_build.append(component)

print(len(components_to_build))
for c in components_to_build:
    print(c.name)
    print(c.tfsPath)

for component in components_to_build:
    pwd = os.getcwd()

    lpath = tfs_path_to_local_path(component.tfsPath, loader.prefix, pwd)
    build_cmd = component.componentBuildCmd
    build(lpath, build_cmd)

    lpath = tfs_path_to_local_path(component.testTfsPath, loader.prefix, pwd)
    print("path: ", lpath)
    build_cmd = component.testBuildCmd
    build(lpath, build_cmd)

    os.chdir(pwd)
