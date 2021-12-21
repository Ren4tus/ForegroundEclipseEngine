﻿using EngineEditor.Utilities;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace EngineEditor.GameProject
{
    [DataContract]
    public class ProjectTemplate
    {
        [DataMember]
        public string? ProjectType { get; set; }

        [DataMember]
        public string? ProjectFile { get; set; }

        [DataMember]
        public List<string>? Folders { get; set; }

        public byte[]? Icon { get; set; }
        public byte[]? Screenshot { get; set; }
        public string? IconFilePath { get; set; }
        public string? ScreenshotFilePath { get; set; }
        public string? ProjectFilePath { get; set; }
    }

    internal class NewProject : ViewModelBase
    {
        // TODO: get the path from the installation location
        private readonly string _templatePath = @"..\..\ForegroundEclipseEngine\ProjectTemplates";

        private string _projectName = "NewProject";
        public string ProjectName
        {
            get => _projectName;
            set
            {
                if (_projectName != value)
                {
                    _projectName = value;
                    ValidateProjectPath();
                    OnPropertyChanged(nameof(ProjectName));
                }
            }
        }

        private string _projectPath = $@"{Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments)}\ForegroundEclipseEngine\";

        public string ProjectPath
        {
            get => _projectPath;
            set
            {
                if (_projectPath != value)
                {
                    _projectPath = value;
                    ValidateProjectPath();
                    OnPropertyChanged(nameof(Path));
                }
            }
        }

        private string _engineType = "NULL";

        public string EngineType
        {
            get => _engineType;
            set
            {
                if (_engineType != value)
                {
                    _engineType = value;
                }
            }
        }



        private bool _isValid;
        public bool IsValid
        {
            get => _isValid;
            set
            {
                if(_isValid != value)
                {
                    _isValid = value;
                    OnPropertyChanged(nameof(IsValid));
                }
            }
        }

        private string _errorMsg;
        public string ErrorMsg
        {
            get => _errorMsg;
            set
            {
                if (_errorMsg != value)
                {
                    _errorMsg = value;
                    OnPropertyChanged(nameof(ErrorMsg));
                }
            }
        }
        private ObservableCollection<ProjectTemplate> _projectTemplates = new ObservableCollection<ProjectTemplate>();
        public ReadOnlyObservableCollection<ProjectTemplate> ProjectTemplates { get; }

        private bool ValidateProjectPath()
        {
            var path = ProjectPath;
            if (!Path.EndsInDirectorySeparator(path))
                path += @"\";
            path += $@"{ProjectName}\";

            IsValid = false;
            if (string.IsNullOrWhiteSpace(ProjectName.Trim()))
            {
                ErrorMsg = "Type in a project name.";
            }
            else if(ProjectName.IndexOfAny(Path.GetInvalidFileNameChars()) != -1)
            {
                ErrorMsg = "Invalid character(s) used in project name.";
            }
            else if (string.IsNullOrWhiteSpace(ProjectPath.Trim()))
            {
                ErrorMsg = "Select a valid project folder.";
            }
            else if (ProjectPath.IndexOfAny(Path.GetInvalidPathChars()) != -1)
            {
                ErrorMsg = "Invalid character(s) used in project path.";
            }
            else if(Directory.Exists(path) && Directory.EnumerateFileSystemEntries(path).Any())
            {
                ErrorMsg = "Selected project folder already exists and is not empty";
            }
            else
            {
                ErrorMsg = string.Empty;
                IsValid = true;
            }
            return IsValid;
        }

        public string CreateProject(ProjectTemplate template)
        {
            ValidateProjectPath();
            if(template == null)
            {
                ErrorMsg = "Please select type of Project.";
                return String.Empty;
            }
            else if (!IsValid)
            {
                return String.Empty;
            }

            if (!Path.EndsInDirectorySeparator(ProjectPath))
                ProjectPath += @"\";
            var path = $@"{ProjectPath}{ProjectName}\";

            try
            {
                if(!Directory.Exists(path))
                    Directory.CreateDirectory(path);
                foreach(var folder in template.Folders)
                {
                    Directory.CreateDirectory(Path.GetFullPath(Path.Combine(Path.GetDirectoryName(path), folder)));
                }
                var dirInfo = new DirectoryInfo(path + @".Primal\");
                dirInfo.Attributes |= FileAttributes.Hidden;
                File.Copy(template.IconFilePath, Path.GetFullPath(Path.Combine(dirInfo.FullName, "Icon.png")));

                
                var projectXml = File.ReadAllText(template.ProjectFilePath);
                projectXml = String.Format(projectXml, ProjectName, ProjectPath);
                var projectPath = Path.GetFullPath(Path.Combine(path, $"{ProjectName}{Project.Extension}"));
                int startPosition = projectXml.LastIndexOf("<EngineType>");
                int endPosition = projectXml.IndexOf("</EngineType>");
                EngineType = projectXml.Substring(startPosition+1, endPosition - startPosition);
                File.WriteAllText(projectPath, projectXml);


                return path;
            }
            catch (Exception ex)
            {
                Logger.Log(MessageType.Error, $"Failed to create {ProjectName}");
                throw;
            }

        }
        public NewProject()
        {
            ProjectTemplates = new ReadOnlyObservableCollection<ProjectTemplate>(_projectTemplates);
            try
            {
                var templatesFiles = Directory.GetFiles(_templatePath, "template.xml", SearchOption.AllDirectories);
                Debug.Assert(templatesFiles.Any());
                foreach (var file in templatesFiles)
                {
                    var template = Utilities.Serializer.FromFile<ProjectTemplate>(file);
                    template.IconFilePath = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(file), "Icon.png"));
                    template.Icon = File.ReadAllBytes(template.IconFilePath);
                    //template.ScreenshotFilePath = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(file), "Screenshot.png"));
                    //template.Screenshot = File.ReadAllBytes(template.ScreenshotFilePath);
                    template.ProjectFilePath = Path.GetFullPath(Path.Combine(Path.GetDirectoryName(file), template.ProjectFile));

                    _projectTemplates.Add(template);
                }
                ValidateProjectPath();
            }
            catch (Exception ex)
            {
                Logger.Log(MessageType.Error, $"Failed to read project templates");
                throw;
            }
        }
    }
}