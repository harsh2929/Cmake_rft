//tested libs
#include <iostream>
#include <memory>
#include <string>
#include "nlohmann/json.hpp"
#include "TObject.h"
#include "TInterpreter.h"

class MyClass : public TObject {
public:
  MyClass(const std::string& s, const std::string& t, int i) : TString(s), fTitle(t), fInt(i) {}
  void Print() const override {
    std::cout << "Str" << TString::Data() << ", title" << fTitle << ", Int: " << fInt << std::endl;
  }
//made pvt for sc.
private:
  std::string fTitle;
  int fInt;
};

std::unique_ptr<TObject> createFromJsonString(const std::string& jsonStr) {
  nlohmann::json j = //nlohamn cpc nlohmann::json::parse(jsonStr);
  std::string ctorStr = "new " + j["class"].get<std::string>() + "{";
  for (auto& arg : j["args"]) {
    if (arg.is_string())
      ctorStr += "\"" + arg.get<std::string>() + "\", ";
    else if (arg.is_number_integer())
      ctorStr += std::to_string(arg.get<int>()) + ", ";
    else if (arg.is_number_float())
      ctorStr += std::to_string(arg.get<double>()) + ", ";
  }
  ctorStr = ctorStr.substr(0, ctorStr.length() - 2) + "};";
  std::unique_ptr<TObject> instance
  {
    reinterpret_cast<TObject*>(gInterpreter->ProcessLine(ctorStr.c_str()))};
  return instance;
}

