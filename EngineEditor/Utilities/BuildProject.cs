using EngineEditor.Components;
using EngineEditor.GameProject;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;

namespace EngineEditor.Utilities
{
    static class BuildProject
    {
        //비주얼 스튜디오 코드로 빌드 - 보류

        //public static bool BuildSucceeded { get; private set; } = true;
        //public static bool BuildDone { get; private set; } = true;
        //private static EnvDTE80.DTE2 _vsInstance = null;
        //private static readonly string _progID = "VisualStudio.DTE.16.0";

        //[DllImport("ole32.dll")]
        //private static extern int CreateBindCtx(uint reserved, out IBindCtx ppbc);

        //[DllImport("ole32.dll")]
        //private static extern int GetRunningObjectTable(uint reserved, out IRunningObjectTable pprot);

        //public static void OpenVisualStudio(string solutionPath)
        //{
        //    IRunningObjectTable rot = null;
        //    IEnumMoniker monikerTable = null;
        //    IBindCtx bindCtx = null;
        //    try
        //    {
        //        if (_vsInstance == null)
        //        {
        //            // Find and open visual
        //            var hResult = GetRunningObjectTable(0, out rot);
        //            if (hResult < 0 || rot == null) throw new COMException($"GetRunningObjectTable() returned HRESULT: {hResult:X8}");

        //            rot.EnumRunning(out monikerTable);
        //            monikerTable.Reset();

        //            hResult = CreateBindCtx(0, out bindCtx);
        //            if (hResult < 0 || bindCtx == null) throw new COMException($"CreateBindCtx() returned HRESULT: {hResult:X8}");

        //            IMoniker[] currentMoniker = new IMoniker[1];
        //            while (monikerTable.Next(1, currentMoniker, IntPtr.Zero) == 0)
        //            {
        //                string name = string.Empty;
        //                currentMoniker[0]?.GetDisplayName(bindCtx, null, out name);
        //                if (name.Contains(_progID))
        //                {
        //                    hResult = rot.GetObject(currentMoniker[0], out object obj);
        //                    if (hResult < 0 || obj == null) throw new COMException($"Running object table's GetObject() returned HRESULT: {hResult:X8}");

        //                    EnvDTE80.DTE2 dte = obj as EnvDTE80.DTE2;
        //                    var solutionName = dte.Solution.FullName;
        //                    if (solutionName == solutionPath)
        //                    {
        //                        _vsInstance = dte;
        //                        break;
        //                    }
        //                }
        //            }

        //            if (_vsInstance == null)
        //            {
        //                Type visualStudioType = Type.GetTypeFromProgID(_progID, true);
        //                _vsInstance = Activator.CreateInstance(visualStudioType) as EnvDTE80.DTE2;
        //            }
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        Debug.WriteLine(ex.Message);
        //        Logger.Log(MessageType.Error, "failed to open Visual Studio");
        //    }
        //    finally
        //    {
        //        if (monikerTable != null) Marshal.ReleaseComObject(monikerTable);
        //        if (rot != null) Marshal.ReleaseComObject(rot);
        //        if (bindCtx != null) Marshal.ReleaseComObject(bindCtx);
        //    }
        //}

        //public static void CloseVisualStudio()
        //{
        //    if (_vsInstance?.Solution.IsOpen == true)
        //    {
        //        _vsInstance.ExecuteCommand("File.SaveAll");
        //        _vsInstance.Solution.Close(true);
        //    }
        //    _vsInstance?.Quit();
        //}
        //private static void OnBuildSolutionBegin(string project, string projectConfig, string platform, string solutionConfig)
        //{
        //    Logger.Log(MessageType.Info, $"Building {project}, {projectConfig}, {platform}, {solutionConfig}");
        //}

        //private static void OnBuildSolutionDone(string project, string projectConfig, string platform, string solutionConfig, bool success)
        //{
        //    if (BuildDone) return;

        //    if (success) Logger.Log(MessageType.Info, $"Building {projectConfig} configuration succeeded");
        //    else Logger.Log(MessageType.Error, $"Building {projectConfig} configuration failed");

        //    BuildDone = true;
        //    BuildSucceeded = success;
        //}

        //public static bool IsDebugging()
        //{
        //    bool result = false;

        //    for (int i = 0; i < 3; ++i)
        //    {
        //        try
        //        {
        //            result = _vsInstance != null &&
        //                (_vsInstance.Debugger.CurrentProgram != null || _vsInstance.Debugger.CurrentMode == EnvDTE.dbgDebugMode.dbgRunMode);
        //        }
        //        catch (Exception ex)
        //        {
        //            Debug.WriteLine(ex.Message);
        //            if (!result) System.Threading.Thread.Sleep(1000);
        //        }
        //    }
        //    return result;
        //}

        //public static void BuildSolution(Project project, string configName, bool showWindow = true)
        //{

        //    if (IsDebugging())
        //    {
        //        Logger.Log(MessageType.Error, "Visual Studio is currently running a process.");
        //        return;
        //    }

        //    OpenVisualStudio(project.Solution);
        //    BuildDone = BuildSucceeded = false;

        //    for (int i = 0; i < 3; ++i)
        //    {
        //        try
        //        {
        //            if (!_vsInstance.Solution.IsOpen) _vsInstance.Solution.Open(project.Solution);
        //            _vsInstance.MainWindow.Visible = showWindow;

        //            _vsInstance.Events.BuildEvents.OnBuildProjConfigBegin += OnBuildSolutionBegin;
        //            _vsInstance.Events.BuildEvents.OnBuildProjConfigDone += OnBuildSolutionDone;

        //            try
        //            {
        //                foreach (var pdbFile in Directory.GetFiles(Path.Combine($"{project.Path}", $@"x64\{configName}"), "*.pdb"))
        //                {
        //                    File.Delete(pdbFile);
        //                }
        //            }
        //            catch (Exception ex) { Debug.WriteLine(ex.Message); }

        //            _vsInstance.Solution.SolutionBuild.SolutionConfigurations.Item(configName).Activate();
        //            _vsInstance.ExecuteCommand("Build.BuildSolution");
        //        }
        //        catch (Exception ex)
        //        {
        //            Debug.WriteLine(ex.Message);
        //            Debug.WriteLine($"Attempt {i}: failed to build {project.Name}");
        //            System.Threading.Thread.Sleep(1000);
        //        }
        //    }
        //}
        //public static bool AddFilesToSolution(string solution, string projectName, string[] files)
        //{
        //    Debug.Assert(files?.Length > 0);
        //    OpenVisualStudio(solution);
        //    try
        //    {
        //        if (_vsInstance != null)
        //        {
        //            if (!_vsInstance.Solution.IsOpen) _vsInstance.Solution.Open(solution);
        //            else _vsInstance.ExecuteCommand("File.SaveAll");

        //            foreach (EnvDTE.Project project in _vsInstance.Solution.Projects)
        //            {
        //                if (project.UniqueName.Contains(projectName))
        //                {
        //                    foreach (var file in files)
        //                    {
        //                        project.ProjectItems.AddFromFile(file);
        //                    }
        //                }
        //            }

        //            var cpp = files.FirstOrDefault(x => Path.GetExtension(x) == ".cpp");
        //            if (!string.IsNullOrEmpty(cpp))
        //            {
        //                _vsInstance.ItemOperations.OpenFile(cpp, EnvDTE.Constants.vsViewKindTextView).Visible = true;
        //            }
        //            _vsInstance.MainWindow.Activate();
        //            _vsInstance.MainWindow.Visible = true;
        //        }
        //    }
        //    catch (Exception ex)
        //    {
        //        Debug.WriteLine(ex.Message);
        //        Debug.WriteLine("failed to add files to Visual Studio project");
        //        return false;
        //    }
        //    return true;
        //}
        static public void BuildToJson(ObservableCollection<Scene> _scenes)
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
        static private void InputJson(string path, ObservableCollection<Scene> _scenes)
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
                        //jsonScene.Add($"{gameEntity.Name}", gameEntity.Name);
                    }
                    //jsonScene.Add($"{scene.Name}", jsonEntityArray);
                    root.Add($"{scene.Name}", jsonEntityArray);
                }
                
            }
            //사용자 정보 배열로 선언
            //var users = new[] { "USER123", "USER2", "USER3", "USER4" };

            //JObject dbSpec = new JObject(
            //    new JProperty("IP", "127.0.0.1"),
            //    new JProperty("ID", "BEOMBEOMJOJO"),
            //    new JProperty("PW", "1234"),
            //    new JProperty("SID", "TEST"),
            //    new JProperty("DATABASE", "TEST")
            //    );

            ////Jarray 로 추가
            //dbSpec.Add("USERS", JArray.FromObject(users));

            File.WriteAllText(path, root.ToString());

        }

        static public void ExectueGame(Project project)
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
