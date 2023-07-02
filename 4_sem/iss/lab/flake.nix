{
  description = "app flake";
  
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  
  outputs = { self, nixpkgs, flake-utils }: flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in rec {
        devShell = pkgs.mkShell rec {
          name = "app";
          buildInputs = [
            pkgs.qt5.qtbase
            pkgs.qt5.qtwayland
            pkgs.qtcreator
            (pkgs.python310.withPackages
              (pythonPkgs: [
                pythonPkgs.sqlalchemy
                pythonPkgs.pyside2
                pythonPkgs.pyside2-tools
                pythonPkgs.python-lsp-server
              ])
            )
          ];
          nativeBuildInputs = [
            pkgs.pkg-config
          ];
          LD_LIBRARY_PATH = "${pkgs.lib.makeLibraryPath buildInputs}";
        };
      }
    );
}
