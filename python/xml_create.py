#import xml.etree.ElementTree as ET
from lxml import etree as ET

def create_xml():
    """
    Creates xml file from input data list
    """

    def indent(elem, level=0):
        i = "\n" + level*"  "
        if len(elem):
            if not elem.text or not elem.text.strip():
                elem.text = i + "  "
            if not elem.tail or not elem.tail.strip():
                elem.tail = i
            for elem in elem:
                indent(elem, level+1)
            if not elem.tail or not elem.tail.strip():
                elem.tail = i
        else:
            if level and (not elem.tail or not elem.tail.strip()):
                elem.tail = i

    # create the file structure
    data = ET.Element('routes')
    items = ET.SubElement(data, 'route')
    items.set('id', '0')
    items.set('map', 'warren')

    for i in range(10):
        item1 = ET.SubElement(items, 'waypoint')
        #item2 = ET.SubElement(items, 'waypoint')
        item1.set('x','1.0')
        item1.set('y','2.0')
        item1.set('z','1.0')
        item1.set('pitch','0.0')
        item1.set('roll','0.0')
        item1.set('yaw','90.0')

    # create a new XML file with the results
    mydata = ET.tostring(data, encoding="unicode")
    #print(mydata)
    mydata = ET.fromstring(mydata)
    tree = ET.ElementTree(mydata)
    indent(mydata)

    tree.write("example.xml", encoding="utf-8", xml_declaration=True)

#create_xml()