{
  description = "Idk";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11";
    # nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: 
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = (import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        }).pkgsi686Linux;
      in {
        devShell = pkgs.mkShell {
          buildInputs = [
            pkgs.gcc
            pkgs.nasm
            pkgs.valgrind
          ];
        };
      }
    );
}
