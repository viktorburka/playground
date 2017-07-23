import xml.etree.ElementTree as XmlParser
from ComponentsLoader import *


class ComponentsLoaderXml(ComponentsLoader):
    def __init__(self, source):
        ComponentsLoader.__init__(self, source)
        self.prefix = ""

    def load(self):
        xml_document = XmlParser.parse(self.source)
        xml = xml_document.getroot()

        self.prefix = xml.find('prefix').text

        for node in xml.iter('component'):
            if node.attrib['enabled'] == 'no':
                continue

            path_element = node.find('component_path')
            test_path_element = node.find('component_test_path')
            component_build_cmd_element = node.find('component_build_cmd')
            test_build_cmd_element = node.find('component_test_build_cmd')
            test_binary_element = node.find('component_test_binary')

            c = Component()
            c.name = node.attrib['name']
            c.tfsPath = self.join_path(self.prefix, path_element.text)
            c.testTfsPath = test_path_element.text
            c.componentBuildCmd = component_build_cmd_element.text
            c.testBuildCmd = test_build_cmd_element.text
            c.testBinary = test_binary_element.text

            dependencies_node = node.find('dependencies')
            if dependencies_node is not None:
                d_list = dependencies_node.findall('dependency')
                for dependency_node in d_list:
                    d = Dependency(dependency_node.text)
                    c.dependencies.append(Dependency(dependency_node.text))

            support_files_node = node.find('support_files')
            if support_files_node is not None:
                s_list = support_files_node.findall('file')
                for file_node in s_list:
                    sf = SupportFile(file_node.text)
                    sf.path_type = file_node.attrib['path_type']
                    c.support_files.append(sf)

            self.components_list.append(c)

        return True

    def join_path(self, left, right):
        if left.endswith("/"):
            left = left[:-1]
        if right.startswith("/"):
            right = right[1:]
        return left + "/" + right
