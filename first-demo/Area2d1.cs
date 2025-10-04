using Godot;
using System;

public partial class Area2d1 : Area2D
{
	public override void _Ready()
	{
	}

	public override void _Process(double delta)
	{
	}

	public void OmAreaEnter(Area2D area)
	{
		GD.Print("碰撞"+area.GetParent().Name);
	}
}
