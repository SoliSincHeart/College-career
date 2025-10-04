using Godot;
using System;

public partial class ProgressBar : Godot.ProgressBar
{
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
        if (Input.IsActionJustPressed("左"))
        {
			this.Value += 50 * delta;
        }
        if (Input.IsActionJustPressed("右"))
        {
            this.Value -= 50 * delta;
        }
    }

	public void onValueChange(float value)
	{
		GD.Print(value);
	}
}