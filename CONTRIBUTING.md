# Contributing

Development, issues, and pull requests happen on
[Forgejo](https://git.barrettruth.com/barrettruth/cp).

## Scope

cp is a competitive programming notebook and solution archive. It is not a
general algorithms library, teaching curriculum, or online judge client.

## Pull Requests

Bug fixes, documentation fixes, and solution fixes are welcome. AI-generated
contributions are not accepted.

For new behavior, open an issue first unless the change is small and already
fits the project's scope.

Changes should keep solutions self-contained and update `README.md` when
appropriate.

## Development

This repo defines a Nix development shell that pins the compiler to the version
used by the judges. Run `nix develop`, or let `direnv` load it automatically.

Solutions are built and run with `just run <file>`, which compiles `<file>` and
feeds it the matching `.in`. Use `just debug <file>` for a sanitiser build.

## Checks

No repository-wide automated check is defined. Compile and test the affected
solution locally before opening a pull request.
