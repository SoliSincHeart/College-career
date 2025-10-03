using Godot;
using System;

public partial class Node2d : Node2D
{
	AudioStreamPlayer player;
	[Export]
	AudioStream bgm;
	public override void _Ready()
	{
		player = new AudioStreamPlayer();
		this.AddChild(player);
		player.Stream = bgm;
		player.Play();
	}

	public override void _Process(double delta)
	{

	}
}
