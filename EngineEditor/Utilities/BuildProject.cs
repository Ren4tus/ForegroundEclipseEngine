using EngineEditor.Components;
using EngineEditor.GameProject;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Windows;

namespace EngineEditor.Utilities
{
    internal static class BuildProject
    {
        public static void BuildToJson(ObservableCollection<Scene> _scenes)
        {
            string path = Directory.GetCurrentDirectory() + @"\test.json";

            //json 파일이 존재 한다면
            if (File.Exists(path))
            {
                MessageBox.Show("새 파일 덮어쓰기 성공");
                InputJson(path, _scenes);
            }
            else
            {
                using (File.Create(path))
                {
                    MessageBox.Show("새 파일 생성 성공");
                }
                InputJson(path, _scenes);
            }
        }

        private static void InputJson(string path, ObservableCollection<Scene> _scenes)
        {
            JObject root = new JObject();
            foreach (Scene scene in _scenes)
            {
                JObject jsonScene = new JObject();
                if (!string.IsNullOrEmpty(scene.Name))
                {
                    JArray jsonEntityArray = new JArray();
                    foreach (GameEntity gameEntity in scene.GameEntities)
                    {
                        jsonEntityArray.Add(gameEntity.Name);
                    }
                    root.Add($"{scene.Name}", jsonEntityArray);
                }
            }
            File.WriteAllText(path, root.ToString());
        }

        public static void ExectueGame(Project project)
        {
            Project.Save(project);
            try
            {
                string gameConfigPath = $@"{project.Path}{project.Name}\";
                if (Directory.Exists($"{project.Path}{project.Name}"))
                {
                    File.WriteAllText($@"{Environment.CurrentDirectory}\config.ini", $"[GameFileRoot]\n{gameConfigPath}");
                }
                Logger.Log(MessageType.Info, "Open Game: " + Environment.CurrentDirectory + @"\" + project.Name + ".exe");
                Process.Start(Environment.CurrentDirectory + @"\" + project.Name + ".exe");
            }
            catch (Exception ex)
            {
                Logger.Log(MessageType.Error, $"Failed to open game");
                throw;
            }
        }
    }
}