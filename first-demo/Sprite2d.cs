using Godot;
using System;

public partial class Sprite2d : Sprite2D
{
	[Export]
	public Texture2D newTexture;

	double timer = 0;
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
		//this.Texture = GD.Load<Texture2D>("res://icon.svg");
		this.Texture = newTexture;
		this.Centered = false;
		this.Offset = new Vector2(2, 0);
		this.FlipH = false;
		this.FlipV = false;
		this.Hframes = 2;
		this.Hframes = 2;
		this.Vframes = 2;
		this.Frame = 0;
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
		timer -= 1;
		if(timer>1)
		{
			timer = 0;
			int index = this.Frame + 1;
			if(index>3)
			{
				index = 0;
			}
			this.Frame = index;
		}
	}
}
