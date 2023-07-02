{
  description = "Hyprland HyprNStack Plugin";

  inputs.hyprland.url = "github:hyprwm/Hyprland";

  outputs = {
    self,
    hyprland,
  }: let
    inherit (hyprland.inputs) nixpkgs;
    withPkgsFor = fn: nixpkgs.lib.genAttrs (builtins.attrNames hyprland.packages) (system: fn system nixpkgs.legacyPackages.${system});
  in {
    packages = withPkgsFor (system: pkgs: {
      hyprNStack = pkgs.callPackage ./. {inherit (hyprland.packages.${system}) hyprland;};
      default = self.packages.${system}.hyprNStack;
    });

    devShells = withPkgsFor (system: pkgs: {
      default = pkgs.mkShell {
        name = "hyprNStack";
        buildInputs = [hyprland.packages.${system}.hyprland];
        inputsFrom = [hyprland.packages.${system}.hyprland];
      };
    });
  };
}
