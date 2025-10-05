using Godot;
using System;

public partial class CharacterBody2d : CharacterBody2D
{

	NavigationAgent2D nav;


    public override void _Ready()
    {
		base._Ready();
		nav = GetNode<NavigationAgent2D>("NavigationAgent2D");
    }
	public override void _PhysicsProcess(double delta)
	{
		base._PhysicsProcess(delta);

        nav.TargetPosition = GetGlobalMousePosition();
		Vector2 dir = nav.GetNextPathPosition() - this.Position.Normalized();
		Velocity = dir * 300;
		GD.Print(this.Position);
		GD.Print(this.Velocity);
		MoveAndSlide();
	}
}
