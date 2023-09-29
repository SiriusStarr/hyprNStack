{
  lib,
  gcc14Stdenv,
  hyprland,
}:
gcc14Stdenv.mkDerivation {
  pname = "hyprNStack";
  version = "0.1";
  src = ./.;

  inherit (hyprland) nativeBuildInputs;

  buildInputs = [hyprland] ++ hyprland.buildInputs;

  dontUseCmakeConfigure = true;

  installFlags = ["PREFIX=$(out)"];

  installPhase = ''
    runHook preInstall

    mkdir -p $out/lib
    mv nstackLayoutPlugin.so $out/lib/libhyprNStack.so

    runHook postInstall
  '';
  meta = with lib; {
    homepage = "https://github.com/zakk4223/hyprNStack";
    description = "Hyprland HyprNStack Plugin";
    platforms = platforms.linux;
  };
}
