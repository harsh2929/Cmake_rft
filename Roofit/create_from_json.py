import json
import ROOT

def create_from_json(class_name, args):
    json_str = json.dumps({"class": class_name, "args": args})
    return ROOT.createFromJsonString(json_str)

obj_1 = create_from_json("MyClass", ["first", "instance", 1])
obj_1.Print()