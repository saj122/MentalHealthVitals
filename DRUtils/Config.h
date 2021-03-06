#ifndef CONFIG_H
#define CONFIG_H

#include <rapidjson/document.h>

#include <glog/logging.h>

#include <string>
#include <fstream>

namespace MHV
{
    class Config
    {
        public:
            inline static std::string _json;
            inline static rapidjson::Document _doc;

        public:
            static void loadConfig()
            {
                readSettings();
                _doc.Parse(getJSONStr());

                if(!_doc.IsObject())
                    LOG(FATAL) << "Settings failed to load.";

                if(!_doc.HasMember("Source"))
                    LOG(FATAL) << "Malformed settings file: Need camera source. (ex. V4L, OpenNI, AVFoundation)";
                if(!_doc.HasMember("Type"))
                    LOG(FATAL) << "Malformed settings file. Need camera type. (ex. RGB, RGBD)";
                if(!_doc.HasMember("Width"))
                    LOG(FATAL) << "Malformed settings file. Need camera image width.";
                if(!_doc.HasMember("Height"))
                    LOG(FATAL) << "Malformed settings file. Need camera image height.";
            }

            static std::string getSource()
            {
                return _doc["Source"].GetString();
            }

            static std::string getType()
            {
                return _doc["Type"].GetString();
            }

            static int getWidth()
            {
                return _doc["Width"].GetInt();
            }

            static int getHeight()
            {
                return _doc["Height"].GetInt();
            }
        private:
            static void readSettings()
            {
#ifndef CONFIG_PATH
                LOG(FATAL) << "Config path not set in cmake.";
#endif
                std::string line;
                std::ifstream in(CONFIG_PATH);
                while(std::getline(in, line))
                {
                    _json += line + "\n";
                }
            }

            static const char* getJSONStr()
            {
                return _json.c_str();
            }
    };
}

#endif // CONFIG_H
