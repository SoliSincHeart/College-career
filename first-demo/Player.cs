using Godot;
using System;

public partial class Player : Sprite2D
{
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{

	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
		if(Input.IsActionJustPressed("右"))
		{
			var enemys = this.GetTree().GetNodesInGroup("敌人");

			foreach(Node enemy in enemys)
			{
				enemy.QueueFree();
			}
		}
		if(Input.IsActionJustPressed("左"))
		{
			this.GetTree().CallGroup("敌人","test");
		}
        if (Input.IsActionJustPressed("上"))
        {
            this.AddToGroup("敌人");
        }
    }
}
