{
  description = "Vartslang dev environment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux"; # or "aarch64-darwin" for Apple Silicon
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShells.${system}.default = pkgs.mkShell {
        buildInputs = with pkgs; [
          gcc
          gdb
          gnumake
          binutils
          valgrind
        ];
        
        # Optional: Run commands when entering the shell
        shellHook = ''
          echo "environment"
        '';
      };
    };
}
