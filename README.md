Recently, there has been some discussion about top Geometry Dash players using an "input buffer" (or something similar). So, I decided to create an input buffer and release it to the public. Since the mod that was always being talked about isn't publicly available, I decided to create one myself and share it with you.

Q: What exactly does it do?
A: Geometry Dash runs its physics at 240 steps per second, so a "frame" here means one physics step — roughly 4 milliseconds. Your click is normally honoured exactly as long as you hold it. This mod holds it longer than you did.

With 6 extra frames, a click that lasted 1 frame becomes 7. Short taps get extended, so a tap that lands slightly too early or too late still registers.

What that gets you in practice
Late taps. You tap just before hitting the ground instead of on it — the extension keeps you holding through the landing.
Early taps. You tap a hair before an orb or a pad, and the hold is still active when the timing window opens.
Chained inputs. Jump, jump, jump at the right rhythm: each buffered release feeds into the next press more forgivingly.
The practical effect is a wider input window. On a hard level where the timing is tight, that's often the difference between a run that dies and one that continues.

Where the menu is
Pause the game and press the gear icon in the bottom-right corner. You'll get a slider from 0 to 30, which starts at 6. Set 0 to turn the buffering off entirely, or crank it up to 30 to see just how much slack the mod can give you. You can also reach it from Geode's mod list, and there's an Enabled switch on the same screen.

Changes apply right away — no restart.

Worth knowing
It works in normal play and editor playtest, because both run on the same layer the mod hooks.
6 frames is ~25 ms. If the level still feels hard, try 15–30 before assuming it isn't working.
A level you beat or verify with this on doesn't count. Turn it off before you verify or upload anything, since the game only sees the inputs the mod forwarded, not the ones you actually made.
If you want to feel the difference immediately, put it on a level you can already beat and try tapping deliberately early and late to see how much it forgives.
