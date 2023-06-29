{
  description = "app flake";
  
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-22.11";
    flake-utils.url = "github:numtide/flake-utils";
  };
  
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };
      in rec {
        devShell = pkgs.mkShell rec {
          name = "app";
          buildInputs = [
            pkgs.gtk3
            pkgs.gtk3.dev
            pkgs.protobuf
            pkgs.steam-run
          ];
          nativeBuildInputs = [
            pkgs.pkg-config
          ];
          LD_LIBRARY_PATH = "${pkgs.lib.makeLibraryPath buildInputs}";
          LIBRARY_PATH = "${pkgs.lib.makeLibraryPath buildInputs}";
        };
      }
    );
}
