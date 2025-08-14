A simple Geode mod that lets you edit your saved account ID directly in the game.

### Features

- Edit your account ID without external tools
- Changes are saved automatically
- Clean integration into the account login screen
- Customizable input label and callback system for mod devs

### Usage

1. Open the account login (or Refresh Login) screen in Geometry Dash
2. Find the new "Account ID" input field
3. Enter your desired account ID
4. Changes save automatically after a short delay

### For Developers

This mod provides an API for other mods without any reason:

```cpp
EditAccountID::get()->onNewID([](int id) {
    // Your code here
});
EditAccountID::get()->m_inputLabel = "lol";
```

Available callbacks:
- `onNewID` - When account ID changes
- `onInputSetup` - When input field is created
- `onLabelSetup` - When label is created
- `onInputTextChanged` - When input text changes
- `onAccountLoginLayerShow` - When login layer appears
- `onAccountLoginLayerSetup` - When login layer is set up

## The truth
This mod was made for ability to refresh login for account with other id, preserving all save data (avoid unlink).

It will not help you login to other people's accounts, you still need a password for this. 
The fact is that even if the password and name of the old and new acc 
are same, game still will check the IDs. That's what the mod was for.