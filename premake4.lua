lib_name = "sinxml"

solution (lib_name)
	configurations { "Debug", "Release" }

	project (lib_name)
		kind "SharedLib"
		language "C++"
		location "build"
		files { lib_name .. "/*.cpp" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

	project ("Test")
		kind "ConsoleApp"
		language "C++"
		location "build/test"
		files { "test/*.cpp" }
		links ( {lib_name} )
		includedirs { "./" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
 
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

newaction {
	trigger     = "install",
	description = "Install the software",
	execute = function ()
		print ("Installing header files to " .. _OPTIONS["prefix"] .."include/")
		os.mkdir(_OPTIONS["prefix"].."include/"..lib_name.."/");
		files = os.matchfiles(lib_name.."/*.h")
		for k, f in pairs(files) do
			print ("Copying " .. f)
			os.copyfile(f, _OPTIONS["prefix"].."include/"..lib_name.."/")
		end

		print ("Installing lib"..lib_name..".so to " .. _OPTIONS["prefix"] .."lib/")
		os.mkdir(_OPTIONS["prefix"].."lib/");
		os.copyfile("lib"..lib_name..".so", _OPTIONS["prefix"].."lib/")
	end
}

newoption {
   trigger     = "prefix",
   value       = "install directory",
   description = "Choose a path to install dir",
}

if not _OPTIONS["prefix"] then
   _OPTIONS["prefix"] = "/usr/local/"
end
