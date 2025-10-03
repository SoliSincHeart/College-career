using Godot;
using System;

public partial class A : Sprite2D
{

	[Signal]
	public delegate void MySignalEventHandler();
	public override void _Ready()
	{

	}

	public override void _Process(double delta)
	{
		if (Input.IsActionJustPressed("左"))
		{
			EmitSignal("MySignal");
		}
	}
}
