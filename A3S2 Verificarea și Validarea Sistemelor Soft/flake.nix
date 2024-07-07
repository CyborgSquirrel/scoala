{
  description = "A very basic flake";
  
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  
  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in {
        devShell = pkgs.mkShell rec {
          name = "vvss";
            NIX_LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
              pkgs.xorg.libX11
              pkgs.xorg_sys_opengl
              pkgs.libglvnd
              pkgs.gtk4
              pkgs.gtk4.dev
            ];
        };
      }
    );
}
