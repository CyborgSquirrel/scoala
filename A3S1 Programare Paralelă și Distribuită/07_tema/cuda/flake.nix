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
  };

  outputs = { self, nixpkgs, flake-utils }: 
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          config.allowUnfree = true;
        };
        meta = {
          name = "conv-cu";
          buildInputs = [
            pkgs.cudatoolkit
            pkgs.linuxPackages.nvidia_x11
            pkgs.stdenv
            pkgs.addOpenGLRunpath
            pkgs.bear
          ];
          src = ./.;
          # dontUnpack = true;
          # shellHook = ''
          #   export CUDA_PATH=${pkgs.cudatoolkit}
          #   # export LD_LIBRARY_PATH=${pkgs.linuxPackages.nvidia_x11}/lib:${pkgs.ncurses5}/lib
          #   export EXTRA_LDFLAGS="-L/lib -L${pkgs.linuxPackages.nvidia_x11}/lib"
          #   export EXTRA_CCFLAGS="-I/usr/include"
          # '';
          buildPhase = ''
            # export CUDA_PATH=${pkgs.cudatoolkit}
            # # export LD_LIBRARY_PATH=${pkgs.linuxPackages.nvidia_x11}/lib:${pkgs.ncurses5}/lib
            # export EXTRA_LDFLAGS="-L/lib -L${pkgs.linuxPackages.nvidia_x11}/lib"
            # export EXTRA_CCFLAGS="-I/usr/include"

            echo hi
            ls
            make
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp target/conv-cu $out/bin
          '';
          postFixup = ''
            addOpenGLRunpath $out/bin/conv-cu
          '';
        };
      in {
        devShell = pkgs.mkShell meta;
        packages.default = pkgs.stdenv.mkDerivation meta;
      }
    );
}
