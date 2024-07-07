{
  description = "Cuda";

  nixConfig.extra-substituters = [
    "https://cuda-maintainers.cachix.org"
    "https://numtide.cachix.org"
  ];
  nixConfig.extra-trusted-public-keys = [
    "cuda-maintainers.cachix.org-1:0dq3bujKpuEPMCX6U4WylrUDZ9JyUG0VpVZa7CNfq5E="
    "numtide.cachix.org-1:2ps1kLBUWjxIneOy1Ik6cQjb41X0iXVXeHigGmycPPE="
  ];

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-23.11";
    # nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    conv-cu.url = "path:./cuda";
  };

  outputs = { self, nixpkgs, flake-utils, conv-cu }: 
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };
        meta = {
          buildInputs = [
            conv-cu.packages.${system}.default
          ];
        };
      in {
        devShell = pkgs.mkShell meta;
      }
    );
}
