from jinja2 import Environment, FileSystemLoader
import xml.etree.ElementTree as ET

# Parse the ARXML file
tree = ET.parse('./GeneratedFiles/Config.xml')
root = tree.getroot()
print(root)
# Extract data from the XML tree
events = []
tasks = []
resources = []
hooks = {}
Interrupts = []

# Extract Events, Resources, and Tasks as before

# Handle Hooks element (potentially missing)
hooks_elem = root.find('.//Hooks')
if hooks_elem is not None:
    hooks["OsErrorHook"] = hooks_elem.find('./OsErrorHook').text == 'true'
    hooks["OsPreTaskHook"] = hooks_elem.find('./OsPreTaskHook').text == 'true'
    hooks["OsPostTaskHook"] = hooks_elem.find('./OsPostTaskHook').text == 'true'
    hooks["OsStartupHook"] = hooks_elem.find('./OsStartupHook').text == 'true'
    hooks["OsShutdownHook"] = hooks_elem.find('./OsShutdownHook').text == 'true'

# Extract Events with mask property
mask = 1
for event_elem in root.findall('.//Event'):
    event_name = event_elem.find('./OsEventName').text
    events.append({"name": event_name, "mask": mask})
    mask <<= 1

# Extract Resources
for resource_elem in root.findall('.//Resource'):
    resource_name = resource_elem.find('./OsResourceName').text
    resource_ceiling_priority = int(resource_elem.find('./OsResourceCeilingPriority').text)
    resource_property = int(resource_elem.find('./OsResourceProperty').text)
    resources.append({"OSResourceName": resource_name, "OSResourceCeilingPriority": resource_ceiling_priority, "OSResourceProperty": resource_property})


#Extract Interrupts has OsInterruptID, OsInterruptCategory, and OsInterruptPriority, OsTaskResourceRef
for interrupt_elem in root.findall('.//Interrupt'):
    interrupt_id = interrupt_elem.find('./OsInterruptID').text
    interrupt_category = interrupt_elem.find('./OsInterruptCategory').text
    interrupt_priority = int(interrupt_elem.find('./OsInterruptPriority').text)
    interrupt_resource_refs = [ref.text for ref in interrupt_elem.findall('.//ResourceRef')]
    Interrupts.append({
        "OsInterruptID": interrupt_id,
        "OsInterruptCategory": interrupt_category,
        "OsInterruptPriority": interrupt_priority,
        "OsInterruptResourceRef": interrupt_resource_refs
    })

# Extract Tasks
for task_elem in root.findall('.//Task'):
    task_name = task_elem.find('./OsTaskName').text
    task_activation = int(task_elem.find('./OsTaskActivation').text)
    task_priority = int(task_elem.find('./OsTaskPriority').text)
    task_schedule = task_elem.find('./OsTaskSchedule').text
    task_type = task_elem.find('./OsTaskType').text
    task_event_refs = [ref.text for ref in task_elem.findall('.//EventRef')]
    if len(task_event_refs) > 0:
        task_event_refs = "(" + " | ".join(task_event_refs) + ")"
    else:
        task_event_refs = "0" 
    task_resource_refs = [ref.text for ref in task_elem.findall('.//ResourceRef')]
    task_autostart = task_elem.find('./OsTaskAutostart').text == 'true'

    tasks.append({
        "OSTaskName": task_name,
        "OsTaskActivation": task_activation,
        "OsTaskPriority": task_priority,
        "OsTaskSchedule": "TASK_FULL" if task_schedule == "FULL" else "TASK_NON",
        "OsTaskType": 1 if task_type == "EXTENDED" else 0,
        "OsTaskEventRef": task_event_refs,
        "OsTaskResourceRef": task_resource_refs,
        "OsTaskAutostart": task_autostart
    })


print(tasks)
print(hooks)
print(resources)
print(events)
print(Interrupts)

# Create an env object for OsConfig.c
env = Environment(loader=FileSystemLoader("."))

# Load the template file
template = env.get_template("./GeneratedFiles/template.c")

# Render the template with the extracted data
rendered_template = template.render(events=events, tasks=tasks, resources=resources, hooks=hooks, Interrupts=Interrupts)

# Write the rendered template to a new file or do something with it
with open("./GeneratedFiles/OsGenerated.h", "w") as file:
    file.write(rendered_template)
