/**
 * @file file_writer.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <fstream>
#include <iostream>

// Engine includes //
#include "file_writer.hpp"
#include "trace.hpp"
#include "transform.hpp"

using namespace rapidjson;

/**
 * @brief Creates root object to write data into
 * 
 */
File_Writer::File_Writer() {
    root.SetObject();
}

/**
 * @brief Writes all the data stored in root to the given filename
 * 
 * @param filename 
 */
void File_Writer::Write_File(std::string filename) {
    std::string fileToOpen = filename;
    FILE* file = fopen(fileToOpen.c_str(), "w");

    char buffer[65536];
    FileWriteStream stream(file, buffer, sizeof(buffer));

    PrettyWriter<FileWriteStream> writer(stream);
    writer.SetMaxDecimalPlaces(3);
    writer.SetFormatOptions(kFormatSingleLineArray);
    root.Accept(writer);

    fclose(file);
}

/**
 * @brief Write a glm::vec3 into root
 * 
 * @param valueName Name of glm::vec3
 * @param value glm::vec3 to write
 */
void File_Writer::Write_Vec3(std::string valueName, glm::vec3 value) {
      // Storing glm::vec3 in array that rapidjson can write
    Value vector3(kArrayType);
    vector3.PushBack(value.x, root.GetAllocator());
    vector3.PushBack(value.y, root.GetAllocator());
    vector3.PushBack(value.z, root.GetAllocator());

      // Writing vector3 into root
    Value name(valueName.c_str(), SizeType(valueName.size()), root.GetAllocator());
    root.AddMember(name, vector3, root.GetAllocator());
}

/**
 * @brief Write a std::string into root
 * 
 * @param valueName 
 * @param value 
 */
void File_Writer::Write_String(std::string valueName, std::string value) {
      // Storing std::string in variable rapidjson can write
    Value name(valueName.c_str(), SizeType(valueName.size()), root.GetAllocator());
    Value newValue(value.c_str(), SizeType(value.size()), root.GetAllocator());
    
    root.AddMember(name, newValue, root.GetAllocator());
}

/**
 * @brief Writing behaviorNames into nested object and then into root
 * 
 * @param behaviorNames 
 */
void File_Writer::Write_Behavior_Name(std::vector<std::string>& behaviorNames) {
    Value behaviors(kObjectType);

      // Filling object
    for (unsigned i = 0; i < behaviorNames.size(); ++i) {
        std::string behaviorName = std::string("behavior_" + std::to_string(i));
        Value name(behaviorName.c_str(), SizeType(behaviorName.size()), root.GetAllocator());

        behaviors.AddMember(name, StringRef(behaviorNames[i].c_str()), root.GetAllocator());
    }

      // Nesting object into root
    root.AddMember("behaviors", behaviors, root.GetAllocator());
}

/**
 * @brief Writing data of an object into root
 * 
 * @param object 
 */
void File_Writer::Write_Object_Data(Object* object) {
    if (!object) return;

      // Getting transform data from object
    Transform* transform = object->GetComponent<Transform>();
    glm::vec3 startPos = { 0.f, 0.f, 0.f };
    glm::vec3 startScale = { 1.f, 1.f, 1.f };
    if (transform) startPos = transform->GetStartPosition();
    if (transform) startScale = transform->GetScale();

      // Putting position into value rapidjson can use
    Value pos(kArrayType);
    pos.PushBack(startPos.x, root.GetAllocator());
    pos.PushBack(startPos.y, root.GetAllocator());
    pos.PushBack(startPos.z, root.GetAllocator());

      // Putting scale into value rapidjson can use
    Value scale(kArrayType);
    scale.PushBack(startScale.x, root.GetAllocator());
    scale.PushBack(startScale.y, root.GetAllocator());
    scale.PushBack(startScale.z, root.GetAllocator());

      // Creating and filling object
    Value objectData(kObjectType);

    Value objectName(object->GetName().c_str(), SizeType(object->GetName().size()), root.GetAllocator());
    objectData.AddMember(StringRef("objectName"), objectName, root.GetAllocator());
    Value templateName(object->GetTemplateName().c_str(), SizeType(object->GetTemplateName().size()), root.GetAllocator());
    objectData.AddMember(StringRef("templateName"), templateName, root.GetAllocator());
    objectData.AddMember(StringRef("position"), pos, root.GetAllocator());
    objectData.AddMember(StringRef("scale"), scale, root.GetAllocator());

      // Nesting object into root
    std::string objectIdName = "object_" + std::to_string(object->GetId());
    Value name(objectIdName.c_str(), SizeType(objectIdName.size()), root.GetAllocator());
    root.AddMember(name, objectData, root.GetAllocator());
}
