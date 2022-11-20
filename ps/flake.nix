{
  description = "A very basic flake";
  inputs.nixpkgs.url = "github:nixos/nixpkgs/d1c3fea7ecbed758168787fe4e4a3157e52bc808";
  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in {
        devShell = pkgs.mkShell rec {
          name = "ps-dev";
          nativeBuildInputs = [
            (pkgs.octave.withPackages (ps: with ps; [ statistics ]))
          ];
          LD_LIBRARY_PATH = "";
        };
      }
    );
}
