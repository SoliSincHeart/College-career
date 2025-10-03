using Godot;
using System;

public partial class MyButton : Button
{
	public override void _Ready()
	{
		this.Connect("pressed",new Callable(this,"buttonClick"));
	}

	public override void _Process(double delta)
	{

	}

	public void buttonClick()
	{
		Node node = GetNode<Node>("/root/Node2D/Sprite2D");
		node.QueueFree();
	}
}
