Jakub Pawlikowski - 400011899
Tyler Philips - 400017512

3GC3 Final Project

Paintball shooting range simulator!

Player standing behind shooting range table can shoot various paintballs at wall.
Player has options for paintball colours, movement of aiming crosshair and horizontal movement
behind shooting table.

Press 'c' to toggle keyboard+arrow key and mouse controls.

Both splatters and paintballs are stored in vectors. Two lights have been enabled in the environment and
material properties have been applied to the paintballs. We made firing more realistic in the way the
crosshairs movement and player position affects the location the paintball lands.

Please note that the program functions best if the window is 500x500

Notes:
project compiles on gpu1 however we are having issues with the x11 forwarding giving us error:
-------------------
X Error of failed request:  BadValue (integer parameter out of range for operation)
  Major opcode of failed request:  150 (GLX)
  Minor opcode of failed request:  24 (X_GLXCreateNewContext)
  Value in failed request:  0x0
  Serial number of failed request:  33
  Current serial number in output stream:  34
-------------------

works cited
https://stackoverflow.com/questions/2183270/what-is-the-easiest-way-to-print-text-to-screen-in-opengl
https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl

Link to github repository: 
https://github.com/JPawlikowski/3GC3_Project/tree/develop

