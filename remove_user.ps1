# Specify the threshold time for identifying "new" accounts (30 minutes ago)
$thresholdTime = (Get-Date).AddMinutes(-30)
Write-Host "Time: $(Get-Date)"
Write-Host "Time: $($thresholdTime)"

$newAccounts = Get-LocalUser | Where-Object { $_.PasswordLastSet -ge $thresholdTime }
Write-Host "Time: $($newAccounts)"

# Specify the path for the CSV log file
$logFilePath = "C:\users\awind\downloads\removed_user.txt"

# Create an array to store log entries
$logEntries = @()

# Remove the new accounts and log the details
foreach ($account in $newAccounts) {
    $logEntry = [PSCustomObject]@{
    	AccountName = $account.Name
    	RemovalTime = Get-Date
    }

    Remove-LocalUser -Name $account.Name
    Write-Host "Removed user account: $($account.Name)"

    $logEntries += $logEntry
}

# Export the log entries to a CSV file
$logEntries | Export-Csv -Path $logFilePath -Append -NoTypeInformation

Start-Sleep -Seconds 10
.\remove_user.ps1