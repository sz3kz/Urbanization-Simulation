.PHONY: clean init test run
.SILENT:

PREREQS := make ninja cmake pre-commit git g++ clang-format clang-tidy cppcheck 

DIRECTORY_BUILD = build/
BUILD_SYSTEM="Ninja"
BUILD_SYSTEM_COMMAND=ninja

check-prerequesites:
	echo "[?] Prerequisite Check:"
	for tool in $(PREREQS); do \
		printf "\tChecking Prerequisite %-15s " "$$tool:"; \
		if command -v $$tool >/dev/null 2>&1; then \
			echo "Installed!"; \
		else \
			echo "MISSING!"; exit 1; \
		fi; \
	done
	echo "[*] Prerequisite Check Ended Successfully!"

clean:
	echo "[?] Removing ${DIRECTORY_BUILD} ... "
	rm -rf ${DIRECTORY_BUILD}
	echo "[*] Done!"
	echo "[?] Uninstalling pre-commit-hooks ... "
	echo -en "\t"
	pre-commit uninstall
	echo -en "\t"
	pre-commit uninstall --hook-type pre-push
	echo "[*] Done!"

init: check-prerequesites clean
	echo "[?] Installing pre-commit hooks ... "
	echo -en "\t"
	pre-commit install
	echo -en "\t"
	pre-commit install --hook-type pre-push
	echo "[*] Done"
	echo "[?] Initializing CMake ... "
	cmake -S . -B ${DIRECTORY_BUILD} -G ${BUILD_SYSTEM}
	echo "[*] Done!"

test:
	echo "[?] Running tests ... "
	cd ${DIRECTORY_BUILD} && ${BUILD_SYSTEM_COMMAND} run_tests
	echo "[*] Done ... "

run:
	echo "[*] Starting simulation: "
	cd ${DIRECTORY_BUILD} && ${BUILD_SYSTEM_COMMAND} run_simulation