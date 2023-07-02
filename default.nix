{
  lib,
  stdenv,
  hyprland,
}:
stdenv.mkDerivation {
  pname = "hyprNStack";
  version = "0.1";
  src = ./.;

  inherit (hyprland) nativeBuildInputs;

  buildInputs = [hyprland] ++ hyprland.buildInputs;

  meta = with lib; {
    homepage = "https://github.com/zakk4223/hyprNStack";
    description = "Hyprland HyprNStack Plugin";
    platforms = platforms.linux;
  };
}
