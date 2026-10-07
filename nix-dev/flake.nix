{
  description = "Vim programming exercises (extends nix-dev-base)";

  inputs = {
    base.url = "path:/home/onyr/nix-dev-base";
    nixpkgs.follows = "base/nixpkgs";
    flake-utils.follows = "base/flake-utils";
  };

  outputs = { base, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; config.allowUnfree = true; };
      in {
        devShells.default = pkgs.mkShell {
          inputsFrom = [ base.devShells.${system}.default ];
          packages = with pkgs; [ vim rustc cargo ];
          shellHook = ''
            echo "[job-interview-training] Vim, C++, Python and Rust shell active."
          '';
        };
      });
}
