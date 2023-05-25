{
  description = "A very basic flake";
  
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-19.09";
    flake-utils.url = "github:numtide/flake-utils";
  };
  
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in {
        devShell = pkgs.mkShell rec {
          name = "ai";
          buildInputs = [
            pkgs.cmake
            pkgs.python35Full
            # pkgs.python35Packages.pip
            # pkgs.python35Packages.setuptools
            # pkgs.python35Packages.virtualenv
            # pkgs.python35Packages.opencv4
            # pkgs.python35Packages.Keras
            # # pkgs.python35Packages.tensorflow
            # pkgs.python35Packages.jupyter
            # pkgs.python35Packages.scikitlearn
            # pkgs.python35Packages.numpy
            # pkgs.stdenv.cc.cc.lib
          ];
          LD_LIBRARY_PATH = "${pkgs.lib.makeLibraryPath buildInputs}";
          shellHook = ''
            source ${./.venv/bin/activate}
          '';
        };
      }
    );
}
