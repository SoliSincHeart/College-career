using Godot;
using System;

public partial class Sprite2DText : Sprite2D
{
	public override void _Ready()
	{
		this.Visible = true;
		this.ZIndex = 10;
		this.ZAsRelative = false;

		this.Position = new Vector2(100, 100);
		//this.Rotation = 0.1f;
		//this.RotationDegrees = 30;
		this.Scale = new Vector2(2, 2);
		this.Skew = 30;
	}

	public override void _Process(double delta)
	{
		var pos = GetGlobalMousePosition();
		//GD.Print(pos);
		LookAt(pos);
	}
}
