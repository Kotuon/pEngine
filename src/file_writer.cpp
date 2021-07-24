
// std includes //
#include <fstream>
#include <iostream>

// Engine includes //
#include "file_writer.hpp"
#include "trace.hpp"

using namespace rapidjson;

File_Writer::File_Writer() {
    root.SetObject();
}

void File_Writer::Write_File(std::string filename) {
    std::string fileToOpen = "data/json/" + filename;
    FILE* file = fopen(fileToOpen.c_str(), "w");

    char buffer[65536];
    FileWriteStream stream(file, buffer, sizeof(buffer));

    PrettyWriter<FileWriteStream> writer(stream);
    writer.SetFormatOptions(kFormatSingleLineArray);
    root.Accept(writer);

    fclose(file);
}

void File_Writer::Write_Vec3(std::string valueName, glm::vec3 value) {
    Value vector3(kArrayType);
    vector3.PushBack(value.x, root.GetAllocator());
    vector3.PushBack(value.y, root.GetAllocator());
    vector3.PushBack(value.z, root.GetAllocator());

    Value name(valueName.c_str(), SizeType(valueName.size()), root.GetAllocator());
    root.AddMember(name, vector3, root.GetAllocator());
}

void File_Writer::Write_String(std::string valueName, std::string value) {
    Trace::Message("Value name: " + value + "\n");
    Value name(valueName.c_str(), SizeType(valueName.size()), root.GetAllocator());
    Value newValue(value.c_str(), SizeType(value.size()), root.GetAllocator());
    
    root.AddMember(name, newValue, root.GetAllocator());
}

void File_Writer::Write_Behavior_Name(std::vector<std::string>& behaviorNames) {
    Value behaviors(kObjectType);

    for (unsigned i = 0; i < behaviorNames.size(); ++i) {
        std::string behaviorName = std::string("behavior_" + std::to_string(i));
        Value name(behaviorName.c_str(), SizeType(behaviorName.size()), root.GetAllocator());

        behaviors.AddMember(name, StringRef(behaviorNames[i].c_str()), root.GetAllocator());
    }

    root.AddMember("behaviors", behaviors, root.GetAllocator());
}