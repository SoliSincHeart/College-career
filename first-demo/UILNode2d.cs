using Godot;
using System;
using System.IO;

public partial class UILNode2d : Node2D
{
	public override void _Ready()
	{
		string path = ProjectSettings.GlobalizePath("user://1.txt");
		GD.Print(path);
		File.WriteAllText(path, "testtest");

	}


}
