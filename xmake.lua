set_project("MockCache")

add_rules("mode.debug", "mode.release")

target("mockcache_demo")
    set_languages("cxx20")
    set_kind("binary")
    set_warnings("all", "error")

    add_files("src/**.cpp")
    add_includedirs("src")

    after_build(function (target)
        os.cp(target:targetfile(), "bin/")
    end)
target_end()
