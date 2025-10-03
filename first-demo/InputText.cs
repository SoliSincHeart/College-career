using Godot;
using System;

public partial class InputText : Node
{
	[Export]
	public PackedScene newScene;
	// Called when the node enters the scene tree for the first time.
	public override void _Ready()
	{
	}

	// Called every frame. 'delta' is the elapsed time since the previous frame.
	public override void _Process(double delta)
	{
		if(Input.IsActionJustPressed("左"))
		{
			SceneTree st = this.GetTree();
			//st.ChangeSceneToFile("res://game2.tscn");
			st.ChangeSceneToPacked(newScene);
		}
        if (Input.IsActionJustPressed("右"))
		{
			Node node = newScene.Instantiate();
			this.GetTree().CurrentScene.AddChild(node);
		}


    }
}
