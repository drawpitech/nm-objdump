{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-23.05";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        cc = pkgs.gcc12;

        deriv = name: inputs: pkgs.stdenv.mkDerivation {
          inherit name;
          src = ./.;

          buildInputs = [ cc ] ++ (with pkgs; [ glibc gnumake ]) ++ inputs;
          makeFlags = [ "CC=${cc}/bin/gcc" ];
          hardeningDisable = [ "format" "fortify" ];
          enableParallelBuilding = true;

          buildPhase = ''
            make ${name}
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp ${name} $out/bin
          '';
        };
      in
      rec
      {
        devShells.default = pkgs.mkShell {
          packages = packages.nm.buildInputs ++ (with pkgs; [
            hexyl
            criterion
            gcovr
            ltrace
            valgrind
            python311Packages.compiledb
            gdb
          ]);
        };

        formatter = pkgs.nixpkgs-fmt;
        packages = {
          nm = deriv "my_nm" [ ];
          objdump = deriv "my_objdump" [ ];
        };
      });
}
