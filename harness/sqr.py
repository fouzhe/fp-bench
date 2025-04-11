def execute_program(timeout: int) -> tuple[str, int]:
    import signal
    import subprocess

    try:
        result = subprocess.run(
            ["./program 0 1.00"],
            capture_output=True,
            encoding="utf-8",
            errors="replace",
            shell=True,
            timeout=timeout,
        )
        # Return stderr and the return code
        return result.stderr, result.returncode
    except subprocess.TimeoutExpired as e:
        # Timeout occurred, also ensure to return stderr captured before timeout and return code -signal.SIGKILL
        return e.stderr, -signal.SIGKILL
    except Exception as e:
        # ensure to raise the error if run failed
        raise e
