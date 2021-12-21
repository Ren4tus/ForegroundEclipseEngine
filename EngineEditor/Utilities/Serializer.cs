using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization;
using System.Diagnostics;
using System.Runtime.Serialization.Json;

namespace EngineEditor.Utilities
{
    internal static class Serializer
    {
        public static void ToFile<T>(T instance, string path)
        {
            try
            {
                using var fs = new FileStream(path, FileMode.Create);
                //var serializer = new DataContractJsonSerializer(typeof(T));
                var serializer = new DataContractSerializer(typeof(T));
                serializer.WriteObject(fs, instance);
            }
            catch (Exception ex)
            {
                Logger.Log(MessageType.Error, $"Failed to serialize {instance} to {path}");
                throw;
            }
        }

        internal static T FromFile<T>(string path)
        {
            try
            {
                using var fs = new FileStream(path, FileMode.Open);
                //var serializer = new DataContractJsonSerializer(typeof(T));
                var serializer = new DataContractSerializer(typeof(T));
                T instance = (T)serializer.ReadObject(fs);
                return instance;
            }
            catch (Exception ex)
            {
                Logger.Log(MessageType.Error, $"Failed to deserialize {path}");
                throw;
            }

        }
        public static void ToJSONFile<T>(T instance, string path)
        {
            try
            {
                using var fs = new FileStream(path, FileMode.Create);
                var serializer = new DataContractJsonSerializer(typeof(T));
                serializer.WriteObject(fs, instance);
            }
            catch (Exception ex)
            {
                Logger.Log(MessageType.Error, $"Failed to serialize {instance} to {path}");
                throw;
            }
        }
        internal static T FromJSONFile<T>(string path)
        {
            try
            {
                using var fs = new FileStream(path, FileMode.Open);
                var serializer = new DataContractJsonSerializer(typeof(T));
                T instance = (T)serializer.ReadObject(fs);
                return instance;
            }
            catch (Exception ex)
            {
                Logger.Log(MessageType.Error, $"Failed to deserialize {path}");
                throw;
            }

        }
    }
}
