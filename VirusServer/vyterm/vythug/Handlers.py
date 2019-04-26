from vyterm.vythug.kernel import *
from vyterm.conversion import *
from vyterm.api3_rd import aliyunapi
from threading import Lock
from random import randint
from functools import reduce
from datetime import *

_handleLock = Lock()


class VirusHandler(Handler):
    def __init__(self):
        self.access_connections = {}

    def check(self, client, packet):
        pass

    def over(self, client, packet):
        pass

    @property
    def handlers(self):
        return {
            VirusCommand.Check.value: self.check,
            VirusCommand.Over.value: self.over,
        }

    def logout(self, client):
        pass


ActiveHandlers = {
    OpCommand.Virus.value: VirusHandler(),
}


def handle_packet(client, opcmd, subcmd, packet):
    if opcmd in ActiveHandlers:
        try:
            _handleLock.acquire()
            success = ActiveHandlers[opcmd].execute(client, subcmd, packet)
            return success
        except Exception as e:
            print("Handle packet happend exception:", e)
        finally:
            _handleLock.release()
    else:
        print("Warning: The command %d-%d doesn't contains in active handlers, data maybe lost" % (opcmd, subcmd))
        return False


def handle_logout(client):
    for handler in ActiveHandlers.values():
        try:
            _handleLock.acquire()
            handler.logout(client)
        except Exception as e:
            print("Handle logout happend exception:", e)
        finally:
            _handleLock.release()


if __name__ == '__main__':
    # assert handlers[0].execute(None, 0, strings_to_bytes("Vyterm", "123456"))
    assert not handle_packet(None, -1, 0, 0)
    assert not handle_packet(None, 0, -1, 0)
    print("All tests of vythug.Handlers passed.")
else:
    Caches.get()
