using Godot;
using System;

public partial class RigidBody2d : RigidBody2D
{

	private bool isGround;
	private int count = 0;
	public override void _Ready()
	{
		this.LockRotation = true;
		this.ContactMonitor = true;
		this.MaxContactsReported = 1;
	}

	public override void _PhysicsProcess(double delta)
	{
		base._PhysicsProcess(delta);
		float horizontal = Input.GetAxis("左","右");
		this.LinearVelocity = new Vector2(horizontal * 100,this.LinearVelocity.Y);
		if(Input.IsActionJustPressed("上") && (isGround == true || count<2))
		{
			++count;
            this.LinearVelocity = new Vector2(this.LinearVelocity.X, -300);        
        }
    }

	public void bodyEntered(Node body)
	{
		GD.Print("碰撞");
		count = 0;
		isGround = true;
	}
    public void bodyExited(Node body)
    {
        GD.Print("远离");
        isGround = false;
    }
}
