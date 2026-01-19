import os

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
example = os.environ.get("EPAPER_EXAMPLE", "panel_test")

env.Replace(
    SRC_FILTER=[
        "+<src/common/*>",
        f"+<src/examples/{example}/*>",
        "-<src/*>",
    ]
)

print(f"[select_example] EPAPER_EXAMPLE={example}")
