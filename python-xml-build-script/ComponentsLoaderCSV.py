
class Component:
    def __init__(self):
        self.name = ''
        self.tfsPath = ''
        self.testTfsPath = ''
        self.componentBuildCmd = ''
        self.testBuildCmd = ''
        self.testBinary = ''
        self.dependencies = []
        self.support_files = []


class Dependency:
    def __init__(self):
        self.tfsPath = ''
        self.buildCmd = ''

    def __init__(self, formatted_str):
        parts = formatted_str.strip().replace("{", "").replace("}", "").split("|")
        if len(parts) >= 2:
            self.tfsPath  = parts[0]
            self.buildCmd = parts[1]


class SupportFile:
    def __init__(self):
        self.path = ''
        self.path_type = ''

    def __init__(self, path):
        self.path = path
        self.path_type = ''


class ComponentsLoader:
    def __init__(self, source):
        self.source = source
        self.components_list = []

    def load(self):
        pass

    def components(self):
        return self.components_list

