using Godot;
using System;

public partial class AudioStreamPlayerTest : AudioStreamPlayer
{
	public override void _Ready()
	{

    }

	public override void _Process(double delta)
	{
        if (Input.IsActionJustPressed("左"))
        {
            if (this.Playing == false)
            {
                this.Play();
            }
        }
        if (Input.IsActionJustPressed("右"))
        {
            this.StreamPaused = true;
        }
        if (Input.IsActionJustPressed("下"))
        {
            this.StreamPaused = false;
        }
    }
}
