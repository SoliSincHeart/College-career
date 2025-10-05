using Godot;
using Godot.Collections;
using System;

public partial class JsonTest : Node2D
{
	public override void _Ready()
	{
		Dictionary user1 = new Dictionary();
		Dictionary user2 = new Dictionary();
		user1["Name"] = "李逍遥";
		user1["hp"] = 100;
		user2["Name"] = "王小虎";
		user2["hp"] = 90;
		var users = new Godot.Collections.Array { user1, user2 };
		Dictionary dic = new Dictionary();
		dic["user"] = users;
		string json = Json.Stringify(dic);
        GD.Print(json);

        Dictionary newdic = Json.ParseString(json).AsGodotDictionary();
		var array = newdic["user"].AsGodotArray();
        Dictionary name = array[0].AsGodotDictionary();
		GD.Print(name["Name"]);




    }
}
