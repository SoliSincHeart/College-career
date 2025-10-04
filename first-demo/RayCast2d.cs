using Godot;
using System;
using System.Runtime.InteropServices;

public partial class RayCast2d : RayCast2D
{
	public override void _Ready()
	{
	}

    public override void _Process(double delta)
    {
		base._Process(delta);

    }
	public override void _PhysicsProcess(double delta)
	{
		base._PhysicsProcess(delta);
		if(Input.IsActionJustPressed("左"))
		{
			this.Enabled = false;
		}
        if (Input.IsActionJustPressed("右"))
        {
            this.Enabled = true;
        }
        if (this.IsColliding())
		{
			Area2D area2D = this.GetCollider() as Area2D;
			GD.Print("检测到：" + area2D.Name);
		}
		else
		{
			GD.Print("没有检测到");
		}

    }
}
